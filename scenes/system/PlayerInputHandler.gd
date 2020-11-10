extends InputHandler
class_name PlayerInputHandler

func input_update(delta) -> void:
	if entity.is_playable:
		entity.set_jumping(Input.is_action_just_pressed("jump"))
		
		var right: float = Input.get_action_strength("move_right")
		var left: float = Input.get_action_strength("move_left")
		
		var up: float = Input.get_action_strength("move_up")
		var down: float = Input.get_action_strength("move_down")
		
		entity.set_ladder(Input.is_action_just_pressed("ladder"))
		
		entity.set_moving(Vector2(right-left, down-up))
	else:
		entity.set_moving(Vector2.ZERO)
