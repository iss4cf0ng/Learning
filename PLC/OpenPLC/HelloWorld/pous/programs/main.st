PROGRAM main
VAR
	button : bool AT %IX0.0;
	light : bool AT %QX0.0;
	counter : int;
END_VAR

if button = true then
    light := true;
    counter := true;
else
    light := false;
end_if;

END_PROGRAM