extends Area2D

onready var audio_player: AudioStreamPlayer2D = $FXActivation

var active: bool = false

var active_texture = preload("res://textures/sprites/enviroment/forest_pressure_green_activated.png")

signal activate

func _on_Pressure_body_entered(body):
	if not body is Entity:
		return 
	
	if active == false:
		active = true
		emit_signal("activate")
		$Sprite.texture = active_texture
		audio_player.play()
