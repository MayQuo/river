extends Node2D

onready var bridge_anim = $Enviroment/Bridge/AnimationPlayer

signal cinematic_action_start
signal cinematic_action_finished

func _ready():
	$Enviroment/Platform/Moving.play("moving")
	$Enviroment/Platform2/Moving.play("moving")
func _on_Pressure_activate():
	bridge_anim.play("anim")
	emit_signal("cinematic_action_start", $Enviroment/Bridge)


func _on_AnimationPlayer_animation_finished(anim_name):
	emit_signal("cinematic_action_finished")
