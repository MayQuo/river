extends EntityStateMachine
class_name EntityStateMachineLadder

class _LadderIdle extends EntityState:
	pass
class _LadderMove extends EntityState:
	pass

const IDLE = "idle"
const MOVE = "move"

func _init():
	connect("state_entered", self, "_on_state_entered")
	connect("state_exited", self, "_on_state_exited")
	
	add_state(IDLE, _LadderIdle.new())
	add_state(MOVE, _LadderMove.new())
	
	change_state(IDLE)
	pass

func _on_state_entered():
	if entity == null:
		return
	match state.tag:
		IDLE:
			entity.animated_sprite.play("ladder_idle")
		MOVE:
			entity.animated_sprite.play("ladder_move")
	pass

func update(delta):
	if state == null or entity == null:
		return
		
	.update(delta)
	
	var dir = entity.get_moving().y
	entity.velocity.y = lerp(entity.velocity.y, entity.ladder_speed * dir, entity.acceleration * delta)
	entity.position.x = lerp(entity.position.x, parent.next_ladder.position.x, 0.5)
	
	match state.tag:
		IDLE:
			if abs(entity.get_moving().y) > 0:
				change_state(MOVE)
		MOVE:
			if abs(entity.get_moving().y) <= 0:
				change_state(IDLE)

	pass

func _on_state_exited(old_state):
	pass
