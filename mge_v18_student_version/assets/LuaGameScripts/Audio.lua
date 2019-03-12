--Paths to audio files
math.randomseed(os.clock())
--Button click
ButtonSFX = "mge/Audio/guinea_pig_shriek.wav"		--Path to the sound file.
ButtonVolume = 100                                  --Set a volume between 0 - 100.
ButtonPitch = 1                                     --Default value = 1

--Moving a box
PushSFX = "mge/Audio/baboon2.wav"
PushVolume = 100
PushPitch = 0.8 + (math.random( 0, 4 ) / 10)

--Heartbeat
HeartBeatSFX = "mge/Audio/Breath+Mask.wav"
HeartBeatVolume = 100
HeartBeatPitch = 1
HeartBeatMaxTime = 4.0								--Maximum time between heartbeats in seconds
HeartBeatMinTime = 1.0								--Minumum time between heartbeats in seconds

--Switch
SwitchSFX = "mge/Audio/cougar4.wav"
SwitchVolume = 100
SwitchPitch = 1

--Level Failure
FailureSFX = "mge/Audio/hyena.wav"
FailureVolume = 100
FailurePitch = 1

--Exit
ExitSFX = "mge/Audio/wolf5.wav"
ExitVolume = 100
ExitPitch = 1

--DIALOGUE
DialogueSFX = "mge/Audio/pup1.wav"
DialogueVolume = 100
DialoguePitch = 1

--Background music
MainMenuBG = "mge/Audio/BattleBG.wav"
MainMenuVolume = 50
MainMenuPitch = 1

--InGame Background music
InGameBG = "mge/Audio/Ambience.wav"
InGameVolume = 50
InGamePitch = 1