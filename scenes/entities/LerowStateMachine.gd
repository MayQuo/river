extends StateMachine

onready var idle = $Idle
onready var move = $Move
onready var jump = $Jump

func _ready():
	states = {
		"idle": idle,
		"move": move,
		"jump": jump
	}
	
	#change_state("idle")

func _process(delta):
	if current_state:
		current_state.update(delta)

