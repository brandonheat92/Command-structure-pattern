+++++++++++++++Process and Commands+++++++++++++++++

Process--------------

The Process code holds lists of commands and process them one after another.

The Process manager maintains a list of processes and does them one after another simultaneously.

Commands-------------

The Commands code contains basic commands like moveto, rotate objects in game.

These commands are bunched together and fed to Process class which executes the commands.

Note that here the commands are not executed simultaneously like process manager. 

Next command execution starts after the completion of current command.

++++++++++++++++++++++++++++++++++++++++++++++++++++