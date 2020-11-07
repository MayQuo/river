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

var jump_count: int = 1
var velocity: Vector2 = Vector2()
var health: int = 3
var spawn_point: Vector2 = Vector2()
####################################################################################################
signal health_changed

####################################################################################################
# input pipeline from input handlers (Player, AI)
var moving: float = 0.0 setget set_moving, get_moving
var jumping: bool = false setget set_jumping, get_jumping
####################################################################################################
func _ready():
	spawn_point = global_position

####################################################################################################
func get_jumping() -> bool:
	#if jump_count > 0:
	#	jump_count = jump_count-1
	#	velocity.y = lerp(velocity.y, -jump_height, JUMP_FORCE)
	return jumping
	
func set_jumping(val: bool) -> void:
	jumping = val
####################################################################################################
func set_moving(direction: float) -> void:
	moving = direction

func get_moving() -> float:
	#velocity.x = lerp(velocity.x, hor*movement_speed, acceleration*delta)
	#is_moving_h = true
	#update_flip_h(hor)
	return moving
####################################################################################################
func update_flip_h(hor: float) -> void:
	if hor != 0:
		animated_sprite.scale.x = sign(hor)

####################################################################################################
func play_animation(anim: String) -> void:
	if animated_sprite.animation != anim:
		animated_sprite.play(anim)

####################################################################################################

####################################################################################################
func _process(delta) -> void:
	if is_on_floor() == false:
		velocity.y += GRAVITY * delta * PI
#	elif velocity.y == 0:
#		jump_count = maximum_jump_count
#
	update_flip_h(get_moving())

#	# apply velocity & collision
	velocity = move_and_slide(velocity, Vector2.UP)
	velocity.x = clamp(velocity.x, -movement_speed, movement_speed)
	
####################################################################################################
