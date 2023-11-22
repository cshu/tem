#!/bin/sh
xclip -o -selection clipboard | /opt/u_bin/piper/piper --model /opt/u_bin/piper_voice/en_US-amy-medium.onnx --output_file /tmp/tmp_tts_piper_out.wav
aplay /tmp/tmp_tts_piper_out.wav
