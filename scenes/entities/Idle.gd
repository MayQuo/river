extends State

func enter() -> void:
	entity.velocity = Vector2()
	entity.play_animation("idle")
	
func update(delta: float) -> void:
	if entity.get_moving() != 0:
		state_machine.change_state("move")
	
	if entity.get_jumping():
		state_machine.change_state("jump")
