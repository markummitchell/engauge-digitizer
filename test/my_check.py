#!/usr/bin/python3

# https://stackoverflow.com/questions/20179153/gdb-backtrace-with-no-user-input

def my_signal_handler (event):
  if (isinstance(event, gdb.SignalEvent)):
    log_file_name = "a.out.crash." + str(gdb.selected_inferior().pid) + ".log"
    gdb.execute("set logging file " + log_file_name )
    gdb.execute("set logging on")
    gdb.execute("set logging redirect on")
    gdb.execute("thread apply all bt")
    gdb.execute("q")

gdb.events.stop.connect(my_signal_handler)
gdb.execute("set confirm off")
gdb.execute("set pagination off")
gdb.execute("r")
gdb.execute("q")
