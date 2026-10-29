PROGRAM main
VAR
	button : bool AT %IX1.0;
	light : bool AT %QX1.0;
	counter : int;
END_VAR

IF button THEN
    light := TRUE;
    counter := 1;
ELSE
    light := FALSE;
    counter := 0; 
END_IF;

END_PROGRAM