extends InputHandler
class_name InputHandlerAI

onready var timer = get_parent().get_node("TimerAISwap")
var mode = 0

func _init():
	entity = get_parent() as Entity

func _ready():
	timer.start()

func input_update(delta) -> void:
	
	match mode:
		0:
			entity.set_moving(Vector2(1.0, 0.0))
			entity.set_jumping(false)
		1:
			entity.set_moving(Vector2(0.0, 0.0))
			entity.set_jumping(false)
		2:
			entity.set_moving(Vector2(-1.0, 0.0))
			entity.set_jumping(false)
		3:
			entity.set_jumping(true)


func _on_TimerAISwap_timeout():
	var rng = RandomNumberGenerator.new()
	rng.randomize()
	mode = rng.randi_range(0,3)
	timer.start()
