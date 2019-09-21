# mood

A moodtracker for the command line that doesn’t work yet. I wanted one, so
I built one.

Currently it only writes a line for every invocation into the file
`$HOME/.mood/YYYY-MM.txt` with `YYYY` and `MM` replaced by the current year and
month respectively (so filesize doesn’t blow up).

The line has the format `TIMESTAMP INT` where `TIMESTAMP` is `YYYYMMDDHHMMSS`
and `INT` is whatever integer between 1 and 7 you invoked it with.
