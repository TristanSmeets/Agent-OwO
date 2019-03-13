--Paths to audio files
math.randomseed(os.time()) 
--Button click
ButtonSFX = "mge/Audio/ui_click.wav"		--Path to the sound file.
ButtonVolume = 20                                 --Set a volume between 0 - 100.
ButtonPitch = 1                                     --Default value = 1

--Moving a box
PushSFX = "mge/Audio/box_pushing2.wav"
PushVolume = 5
PushPitch = 0.8 + (math.random( 0, 4 ) / 10)

--Switch
SwitchSFX = "mge/Audio/switch_activated.wav"
SwitchVolume = 50
SwitchPitch = 1

--Level Failure
FailureSFX = "mge/Audio/squeak.wav"
FailureVolume = 10
FailurePitch = 1

--Exit
ExitSFX = "mge/Audio/exit_activated.wav"
ExitVolume = 10
ExitPitch = 1

--DIALOGUE
DialogueSFX = "mge/Audio/text_box.wav"
DialogueVolume = 10
DialoguePitch = 1

--Background music
MainMenuBG = "mge/Audio/BGMusic_4.wav"
MainMenuVolume = 20
MainMenuPitch = 1

--InGame Background music
InGameBG = "mge/Audio/BGMusic_5.wav"
InGameVolume = 10
InGamePitch = 1

--Heartbeat
HeartBeatSFX = "mge/Audio/heartbeat3.wav"
HeartBeatVolume = 100
HeartBeatPitch = 1
HeartBeatMaxTime = 2.0                                --Maximum time between heartbeats in seconds
HeartBeatMinTime = 0.3                               --Minumum time between heartbeats in seconds