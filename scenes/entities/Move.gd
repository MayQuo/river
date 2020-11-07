extends State

func enter() -> void:
	entity.play_animation("move")

func update(delta: float) -> void:
	var dir = entity.get_moving()
	if dir == 0:	
		state_machine.change_state("idle")
	
	entity.velocity.x = lerp(entity.velocity.x, entity.movement_speed * dir, entity.acceleration * delta)
	
	if entity.get_jumping():
		state_machine.change_state("jump")
