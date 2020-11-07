extends InputHandler
class_name PlayerInputHandler

func input_update(delta) -> void:
	if entity.is_playable:
		entity.set_jumping(Input.is_action_just_pressed("jump"))
		
		var right: float = Input.get_action_strength("move_right")
		var left: float = Input.get_action_strength("move_left")
		
		entity.set_moving(right-left)
		
		
