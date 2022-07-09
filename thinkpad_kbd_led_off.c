#include <stdio.h>
#include <stdlib.h>

static char* fname = "/sys/class/leds/tpacpi::kbd_backlight/brightness";
static char* fname_max = "/sys/class/leds/tpacpi::kbd_backlight/max_brightness";
static char buffer[256];
int main(int ac, char **av) {
	FILE *f;
	int  maxval = -1;
	int  desired = -1;

	if ( ac > 2 ) {
		fprintf(stderr,"usage: %s [brightness]\n", av[0]);
		exit(1);
	}
	if ( ac == 1 )
		desired = 0;
	else
		sscanf(av[1],"%d",&desired);
	/* endif */
	if ( (f=fopen(fname_max,"r")) == NULL ) {
		sprintf(buffer,"%s: cannot access kbd leds maxvalue at\n\t%s",
				av[0], fname_max);
		perror(buffer);
		exit(1);
	}
	if ( fscanf(f,"%d",&maxval) != 1 ) {
		sprintf(buffer,"%s: cannot read value from\n\t%s",
				av[0], fname_max);
		perror(buffer);
		exit(2);
	}
	fclose(f);
	if ( ( desired < 0 ) || ( desired > maxval ) ) {
		fprintf(stderr,"%s: wrong value - must be between 0 and %d\n",
				av[0], maxval);
		exit(2);
	}
	if ( (f=fopen(fname,"w")) == NULL ) {
		sprintf(buffer,"%s: cannot access kbd leds at\n\t%s",
				av[0], fname);
		perror(buffer);
		exit(1);
	}
	fprintf(f,"%d",desired);
	fclose(f);
	return 0;
}

