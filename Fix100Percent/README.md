# Fix 100%

A Geode mod for Geometry Dash 2.2081 by damian.

Classic-level progress uses `player X / level length * 100`, even when the level
contains verification-time data. The percentage stays below 100 until the run
is complete. Platformer levels use GD's normal percentage calculation.

The mod hooks `PlayLayer::getCurrentPercent`, which GD uses for the progress bar
and percentage label. It captures that position at death and uses it for New Best
and the saved attempt percentage, then clears it on retry. It does not edit level
layout or hook the completion routine.
Other mods that draw their own percentage counter may calculate it separately.

X-based progress can move backward in levels that reverse the player. Existing
saved bests are not rewritten.

## Build

Install the Geode SDK and set `GEODE_SDK`, then run:

```text
geode build
```

The package is `damian.fix100percent.geode`. Copy it to the game's `geode/mods`
folder and restart Geometry Dash.

## Check the calculation

Build and run `tests/progress.cpp` with a C++23 compiler. In game, check a classic
level with an early 100% display, a normal completion, practice mode, and a
platformer level. Windows builds have been compiled locally; other platforms
need their own build and gameplay checks.

Developed with AI assistance.
