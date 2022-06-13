# Garmin CSV parser
 ### Parses Garmin activities CSV and tabulate rough estimate of current running stress balance

To compile, just type `make` to run the Makefile

Then, the CLI format is `./parse [filename].csv [lactate threshold heart rate]`

The program will then extract `type`, `distance`, `duration`, `average heart rate` from each `Running` activity.

From this, the program will tabulate a Running Stress Score for each activity and a Running Stress Balance over time.

It's obviously not perfect, but it will give you a good 'jumping-off' point to start training.

Techniques I wanted to practice:
- Program modularity
- Makefiles
- structs
- pointers
- time.h library
- linked lists
