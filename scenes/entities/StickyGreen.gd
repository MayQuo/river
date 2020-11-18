extends Entity
class_name StickyGreen

# air states
class air_class extends StateMachine:
	func init():
		.init()
	func update(delta):
		.update(delta)
		if entity.is_on_floor() == false:
			entity.velocity.y += entity.GRAVITY * delta * PI
		elif entity.velocity.y > 0:
			entity.velocity.y = 0

		var dir = entity.get_moving().x
		entity.velocity.x = lerp(entity.velocity.x, entity.movement_speed * dir, entity.acceleration * delta)

	################################################################################################
	class idle extends State:
		func init():
			entity.velocity.x = 0
			entity.play_animation("idle")
		func update(delta):
			if entity.get_moving().x != 0:
				change_state("move")
	
			if entity.get_jumping():
				parent.get("jump").prev = "idle"
				change_state("jump")
				
			if entity.velocity.y > 5:
				change_state("fall")

	################################################################################################
	class move extends State:
		func init():
			entity.play_animation("move")
			
		func update(delta):
			if entity.get_moving().x == 0:	
				change_state("idle")
	
			if entity.get_jumping():
				parent.get("jump").prev = "move"
				change_state("jump")
			
			if entity.velocity.y > 5:
				change_state("fall")
	
	################################################################################################
	class jump extends State:
		var prev
		var landing = false
		
		func init():
			landing = false
			entity.velocity.y = lerp(entity.velocity.y, -entity.jump_height, entity.JUMP_FORCE)
			entity.play_animation("jump")
			
		func update(delta):
			if entity.velocity.y >= 0:
				change_state("fall")
				
	################################################################################################
	class fall extends State:
		var landing = false
		func init():
			landing = false
			entity.play_animation("fall")
		
		func update(delta):
			if entity.is_on_floor() and not landing:
				entity.play_animation("landing")
				landing = true
				yield(entity.animated_sprite, "animation_finished")
				if entity.get_moving().x != 0:
					change_state("move")
				else:
					change_state("idle")

onready var air_states: air_class = air_class.new()

signal body_entered(body, other)
signal body_exited(body, other)

func _ready():
	state_machine.define_state("air", air_states)
	
	air_states.define_state("idle", air_class.idle.new())
	air_states.define_state("move", air_class.move.new())
	air_states.define_state("jump", air_class.jump.new())
	air_states.define_state("fall", air_class.fall.new())
	
	state_machine.change_state("air")
	air_states.change_state("idle")


func _on_Trigger_body_entered(body):
	emit_signal("body_entered", body, self)


func _on_Trigger_body_exited(body):
	emit_signal("body_exited", body, self)
