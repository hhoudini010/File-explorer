File Explorer

A terminal based file explorer with limited functionalities.

Works in two modes : Normal Mode and Command mode.

Normal mode :

-Lists files and directories along with details. 
-Opens files and directories when enter key is pressed.
-Vertical  can be done using arrow keys. (Vertical overflow not handled.)

-Files are opened using open.(xdg-open is not present in Mac Os).

-Traversal can be done using left and right arrow keys, backspace and 'h' keys.

Command Mode :

Mode shifts from Nornal mode to command mode on pressing colon.

All paths are to be provided relative to the root for copy_file, copy_dir, delete_file, delete_dir and goto.

For snapshot command, dumpfile name has to be provided which will be created at application root.

(File Search command not implemented.)

-Create file syntax : create_file foo.txt /abc
(File path is relative from application root)

-Create directory : create_dir folder /abc

-Copy file or directory : copy file_name /abc

-Move file or directory : move file_name /abc

-Rename file : rename old_name new_name

-Delete file : delete_file /abc/file_name

-Delete directory : delete_dir /abc/dir_name

-Goto : goto /dir_name

-Snapshot : snapshot folder_name dumpfile_name.

(Dumpfile will be present on application root.)

On pressing escape key, the application goes back to Normal mode.



