extends State

func enter() -> void:
	entity.velocity.y = lerp(entity.velocity.y, -entity.jump_height, entity.JUMP_FORCE)
	entity.play_animation("jump")
	
func update(delta: float) -> void:
	var prev_state = state_machine.get_prev()
	
	if entity.is_on_floor() and entity.velocity.y >= 0:
		state_machine.change_state(prev_state)
