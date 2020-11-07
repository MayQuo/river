extends Node2D
class_name PlayerController

onready var player = null


func _process(delta):
	if player != null:
		if player.is_playable == true:
			if Input.is_action_just_pressed("jump"):
				player.jump()
	
			var right = int(Input.is_action_pressed("move_right"))
			var left = int(Input.is_action_pressed("move_left"))
			
			player.move(right-left, delta)
		
			position = player.position
