[ScreenElement]

moveable = 1

Num actions	= 2

action 1	= Idle
action 2	= Walk
action 3	= Hide

defaultAction	= Walk

height		= 66
width		= 38

[ScreenEditor]
classification = Characters|Guest stars
name = PhaXm

[Idle]
image	= phaxm_idle.png

numFrames	= 6
Frame delay	= 5

priority 	= 0

[Walk]
image		= phaxm_walk.png

numFrames	= 6
Frame delay	= 3

#forward	= 3
right		= -3

priority 	= 5

# we must have a direction, and not L nor R nor B1
keys		= +DIR -L -R -B1

# as soon as we release the keys, this action must stop.
Always stay	= 0

[Hide]
image		= phaxm_hide.png

numFrames	= 12
Frame delay	= 5
