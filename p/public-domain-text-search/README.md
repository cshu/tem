This grep command avoids printing entire line, just print the part surrounding the match
grep -Iir -oE '.{0,10}\bQUERY STRING\b.{0,10}'
