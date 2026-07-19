#include <stdio.h>
int drake_equation();

int main(int argc, char **argv){
	int N;
	
	/* Set 1 */	
	N = drake_equation(1.0, 0.2, 1, 1.0, 1.0, 0.1, 1000);
	printf("N=%u R*=%0.1f fp=%0.1f ne=%d fl=%0.1f fi=%0.1f fc=%0.1f L=%d\n",\
		N, 1.0, 0.2, 1, 1.0, 1.0, 0.1, 1000);


	/* Set 2 */
	N = drake_equation(1.0, 0.5, 5, 1.0, 1.0, 0.2, 1000000000);
	printf("N=%u R*=%0.1f fp=%0.1f ne=%d fl=%0.1f fi=%0.1f fc=%0.1f L=%d\n",\
		N, 1.0, 0.5, 5, 1.0, 1.0, 0.2, 1000000000);


	/* Set 3 */
	N = drake_equation(1.5, 1.0, 3, 1.0, 0.0001, 0.001, 304);
	printf("N=%u R*=%0.1f fp=%0.1f ne=%d fl=%0.1f fi=%0.1f fc=%.1f L=%d\n",\
		N, 1.5, 1.0, 3, 1.0, 0.0001, 0.001, 304);


	/* Set 4 */
	N = drake_equation(3.0, 1.0, 5, 1.0, 1.0, 0.1, 10000000);
	printf("N=%u R*=%0.1f fp=%0.1f ne=%d fl=%0.1f fi=%0.1f fc=%0.1f L=%d\n",\
		N, 3.0, 1.0, 5, 1.0, 1.0, 0.1, 10000000);

	
	return 0;
}




int drake_equation(double R, double Fp, int Ne, double Fl, double Fi, \
	double Fc, int L){

	unsigned int N;
	N = R * Fp * Ne * Fl * Fi * Fc * L;

	return N;
}