/* Membuat dan membaca kembali file yang setiap rekamannya adalah integer */
#include<stdio.h>
int main(){
	/* Kamus */
	int i;
	int rek;
	int retval;
	FILE *fileku;
	/* ALGORITMA */
	/* Membuat */
	fileku = fopen ("filein.dat", "w");
	for (i=1; i<5; i++){
		/* perhatikan format penulisan */
		retval = fprintf (fileku, "%d", i);
	}
	printf ("\nSelesai membuat ...");
	fclose (fileku);
	/* Membaca kembali */
	fileku = fopen ("filein.dat", "r");
	retval = fscanf (fileku, "%d", &rek); /* harus sama dengan ketika saat dibuat */
	printf ("%d", rek);
	while (retval != EOF){
		printf ("Yang dibaca: %d \n", rek);
		retval = fscanf (fileku, "%d",&rek);
	}
	printf ("\nbye ...");
	fclose (fileku);
	return 0;
}
