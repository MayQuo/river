extends KinematicBody2D
class_name Entity
####################################################################################################
const GRAVITY: float = 80.0
const JUMP_FORCE: float = 1.4

####################################################################################################
export(String) var entity_name = "Entity"

export(float) var movement_speed: float = 100.0
export(float) var acceleration: float = 20.0

export(float) var jump_height: float = 100.0
export(int) var maximum_jump_count: int = 1
export(int) var maximum_health: int = 3

export(bool) var is_playable: bool = false
export(bool) var is_attackable: bool = true

####################################################################################################
onready var animated_sprite = $AnimatedSprite
onready var state_machine = $EntityStateMachine
onready var coyote_timer = $CoyoteTimer
onready var jump_buffer = $JumpBuffer

# standard - animation tag cycles
var animation_tag_move = "move" 
var animation_tag_idle = "idle"
var animation_tag_fall = "fall"
var animation_tag_jump = "jump"
var animation_tag_landing = "landing"

var jump_count: int = 1
var velocity: Vector2 = Vector2()
var health: int = 3
var spawn_point: Vector2 = Vector2()

var moving: Vector2 = Vector2() setget set_moving, get_moving
func set_moving(vec: Vector2) -> void:
	moving.x = vec.x
	moving.y = vec.y
func get_moving() -> Vector2:
	return moving

var jumping: bool = false setget set_jumping, get_jumping
func set_jumping(value: bool) -> void:
	jumping = value
func get_jumping() -> bool:
	return jumping

var ladder: bool = false setget set_ladder, get_ladder
func set_ladder(value: bool) -> void:
	ladder = value
func get_ladder() -> bool:
	return ladder

var push: bool = false setget set_pushing, get_pushing
func set_pushing(value: bool) -> void:
	if push != value:
		emit_signal("push_changed")
	push = value
func get_pushing() -> bool:
	return push

####################################################################################################
signal health_changed
signal push_changed

####################################################################################################

func _ready():
	spawn_point = global_position
	state_machine.parent = self
	if state_machine is EntityStateMachine:
		state_machine.set_entity(self)
	#state_machine.init()
	#state_machine.enter()
	
####################################################################################################
func update_flip_h() -> void:
	if moving.x != 0:
		animated_sprite.scale.x = sign(moving.x)

####################################################################################################
func play_animation(anim: String) -> void:
	if animated_sprite.animation != anim:
		animated_sprite.play(anim)

####################################################################################################
func _process(delta) -> void:
	state_machine.update(delta)

	# apply velocity & collision
	var snap = Vector2.DOWN * 16 if is_on_floor() and not get_jumping() else Vector2.ZERO

	velocity = move_and_slide_with_snap(velocity, snap, Vector2.UP)
	velocity.x = clamp(velocity.x, -movement_speed, movement_speed)

	update_flip_h()
####################################################################################################
