#character definition for Riesz. For now it's quite useless, though.
[CHARACTER]

#max name size is 30 characters
name = Riesz

HP = 20
MP = 20
SP = 20

[ScreenElement]

moveable = 1

Num actions	= 2

action 1	= IDLE
action 2	= WALK

defaultAction	= WALK

width		= 26
height		= 38

[ScreenEditor]
classification = Characters|Playable
name = Riesz

[IDLE]
image	= riesz_idle.png

numFrames	= 1
Frame delay	= 1000

priority 	= 0

[WALK]
image	= riesz_walk.png

numFrames	= 6
Frame delay	= 5
Next action	= -1			# this action 

# for all frames when walking, do the following :
forward		= 2		# advance one pixel in the direction of Riesz


priority 	= 5

# we must have a direction, and not L nor R nor B1
keys		= +DIR -L -R -B1

# as soon as we release the keys, this action must stop.
Always stay	= 0

[TURN_ROUND]
image	= riesz_walk.png

numFrames	= 32
Frame delay	= 5
Next action	= 1

forward		= 2


# special actions should be always higher than the non special actions (the ones which don't
# use the left button key)
priority 	= 100

keys		= +L COMBO(LEFT,DOWN,RIGHT,B2)

; those lines means that every 4 frames, Riesz will turn to her right
[TURN_ROUND frame 4]
rotate_right	= 1

[TURN_ROUND frame 8]
rotate_right	= 1

[TURN_ROUND frame 12]
rotate_right	= 1

[TURN_ROUND frame 16]
rotate_right	= 1

[TURN_ROUND frame 20]
rotate_right	= 1

[TURN_ROUND frame 24]
rotate_right	= 1

[TURN_ROUND frame 28]
rotate_right	= 1

[TURN_ROUND frame 32]
rotate_right	= 1
