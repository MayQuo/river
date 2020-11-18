extends Entity
class_name Lerow

onready var label = $Label

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

		if entity.get_ladder() and entity.next_ladder:
			parent.get("ladder").change_state("idle")
			parent.change_state("ladder")
	
		if entity.get_roll():
			change_state("roll")
	
		if entity.get_dash():
			change_state("dash")
	
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
	
	################################################################################################
	class roll extends State:
		func init():
			entity.play_animation("roll")
			#entity.velocity.x = entity.get_moving().x * 2000.0
			yield(entity.animated_sprite, "animation_finished")
			change_state("idle")
		func update(delta):
			pass
	
	################################################################################################
	class dash extends State:
		var dir = 1.0
		func init():
			entity.play_animation("dash")
			dir = entity.get_moving().x 
			yield(entity.animated_sprite, "animation_finished")
			change_state("idle")
		func update(delta):
			entity.velocity.x += dir * 800.0

###################################################################################################
# water states
class water_class extends StateMachine:
	func init():
		.init()
		
	func update(delta):
		.update(delta)

	################################################################################################
	class idle extends State:
		func init():
			pass
		func update(delta):
			pass
	
	################################################################################################
	class move extends State:
		func init():
			pass
		func update(delta):
			pass
###################################################################################################
# ladder states
class ladder_class extends StateMachine:
	func init():
		.init()
		entity.velocity.x = 0.0
		
	func update(delta):
		.update(delta)
		
		# if entity leaves ladder or toggles ladder again:
		if not entity.next_ladder or entity.get_ladder() == true:
			parent.get("air").change_state("idle")
			parent.change_state("air")
			
		# move the entity to the middle
		if entity.next_ladder:
			entity.position.x = lerp(entity.position.x, entity.next_ladder.position.x, delta* 2.0)
		
			# vertical ladder movement
			var dir = entity.get_moving().y
			entity.velocity.y = lerp(entity.velocity.y, entity.movement_speed * dir, entity.acceleration * delta)
	
	################################################################################################
	class idle extends State:
		func init():
			entity.play_animation("ladder_idle")
			
		func update(delta):
			if entity.get_moving().y != 0:
				change_state("move")

	################################################################################################
	class move extends State:
		func init():
			entity.play_animation("ladder_move")
		func update(delta):
			if entity.get_moving().y == 0:
				change_state("idle")
				
####################################################################################################

var air_states: air_class = air_class.new()
var water_states: water_class = water_class.new()
var ladder_states: ladder_class = ladder_class.new()

var next_ladder: Area2D = null

var roll: bool setget set_roll, get_roll
var dash: bool setget set_dash, get_dash
func set_roll(value: bool) -> void:
	roll = value

func get_roll() -> bool:
	return roll

func set_dash(value: bool) -> void:
	dash = value

func get_dash() -> bool:
	return dash

func _ready():
	
	state_machine.define_state("air", air_states)
	state_machine.define_state("water", water_states)
	state_machine.define_state("ladder", ladder_states)
	
	air_states.define_state("idle", air_class.idle.new())
	air_states.define_state("move", air_class.move.new())
	air_states.define_state("jump", air_class.jump.new())
	air_states.define_state("fall", air_class.fall.new())
	air_states.define_state("roll", air_class.roll.new())
	air_states.define_state("dash", air_class.dash.new())
	
	water_states.define_state("idle", water_class.idle.new())
	water_states.define_state("move", water_class.move.new())
	
	ladder_states.define_state("idle", ladder_class.idle.new())
	ladder_states.define_state("move", ladder_class.move.new())

	state_machine.change_state("air")	
	air_states.change_state("idle")

	air_states.connect("state_changed", self, "_on_air_state_changed")
	ladder_states.connect("state_changed", self, "_on_air_state_changed")

func _process(delta):
	pass
	#print(next_ladder)

func _on_air_state_changed(s):
	label.text = s

func _on_Trigger_area_entered(area):
	var target = area as Area2D
	if target.is_in_group("ladder"):
		next_ladder = target

func _on_Trigger_area_exited(area):
	var target = area as Area2D
	if target.is_in_group("ladder"):
		next_ladder = null

func _on_Trigger_body_entered(body):
	pass # Replace with function body.
