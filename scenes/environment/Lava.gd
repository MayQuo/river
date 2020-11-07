extends Area2D
class_name Lava

func _ready():
	pass

func _on_Lava_body_entered(body):
	if body is Entity:
		body.health -= 1
		body.emit_signal("health_changed")
		body.global_position = body.spawn_point
