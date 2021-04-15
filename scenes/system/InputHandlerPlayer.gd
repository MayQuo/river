extends InputHandler
class_name InputHandlerPlayer

func input_update(delta) -> void:
	if entity.is_playable:
		entity.set_jumping(Input.is_action_pressed("jump"))
		
		var right: float = Input.get_action_strength("move_right")
		var left: float = Input.get_action_strength("move_left")
			
		var up: float = Input.get_action_strength("move_up")
		var down: float = Input.get_action_strength("move_down")
		
		entity.set_ladder(Input.is_action_just_pressed("ladder"))
		#print(entity.get_ladder())
		
		entity.set_moving(Vector2(right-left, down-up))
		
		if entity.is_in_group("lerow"):
			var roll: bool = Input.is_action_just_pressed("roll")
			#var dash: bool = Input.is_action_just_pressed("dash")
			#var slide: bool = Input.is_action_just_pressed("slide")
			var smoke: bool = Input.is_action_just_pressed("smoke")
			
			#var attack: bool = Input.is_action_just_pressed("attack")
			
			entity.set_roll(roll)
			entity.set_smoke(smoke)
			#entity.set_dash(dash)
			#entity.set_attack(attack)
			
	else:
		entity.set_moving(Vector2.ZERO)
	pass
