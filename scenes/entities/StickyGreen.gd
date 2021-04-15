extends Entity
class_name StickyGreen

signal body_entered(body, other)
signal body_exited(body, other)

func _on_Trigger_body_entered(body):
	emit_signal("body_entered", body, self)

func _on_Trigger_body_exited(body):
	emit_signal("body_exited", body, self)
