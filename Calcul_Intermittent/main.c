#include <stdio.h>

#define AJ		31.96f
#define RAPPORT_BRUT_NET_CHANT	1.2485f
#define RAPPORT_BRUT_NET_MUSICIEN	1.26f
#define GLOBAL	1.4823f

#define RAPPORT_GLOBAL_BRUT_CHANT 0.5060
#define RAPPORT_GLOBAL_NET_CHANT	0.5404

static float check_sr_float(float sr, float *reste) {
	float return_val;
	if (sr <= 13700.0f) {
		*reste = 0.0f;
		return_val = sr;
	}
	else {
		*reste = sr-13700.0f;
		return_val = 13700.0f;
	}
	return return_val;
}

static int check_nht(int nht, int *reste) {
	int return_val;
	if (nht <= 690) {
		*reste = 0;
		return_val = nht;
	}
	else {
		*reste = nht-690;
		return_val = 690;
	}
	return return_val;
}

static float calcul_indeminitees(float cachet, int nb) {
	float A, B, C, SJM, ajb, csg, crds, SR2, SR2_reste;
	int NHT, NHT_reste;
	cachet *= RAPPORT_GLOBAL_BRUT_CHANT;
	SR2 = cachet * (float)nb;
	NHT = nb*12;
	SJM = (float)SR2/((float)NHT/10.0f);
	//SR = check_sr(SR, &SR_reste);
	SR2 = check_sr_float(SR2, &SR2_reste);
	NHT = check_nht(NHT, &NHT_reste);
	//printf("NHT reste = %d\nSR reste : %d\n", NHT_reste, SR_reste);
	A = AJ*(0.36f*(float)SR2 + 0.05f*(float)SR2_reste)/5000.0f;
	B = AJ*(0.26f*(float)NHT + 0.08f*(float)NHT_reste)/507.0f;
	C = AJ*0.7f;
	ajb = (A+B+C);
	if (ajb <= 31.96f) {
		csg = 0.0f;
		crds = 0.0f;
	}
	else if (ajb > 31.96f && ajb <= 58.0f) {
		csg = 0.0093f*SJM;
		crds = 0.0f;
	}
	else if (ajb > 58.0f) {
		csg = SJM*0.062f;
		crds = SJM*0.005f;
	}
	printf("\nindemnitées journaliere brut = %f\n", ajb);
	printf("CSG = %f\n", csg);
	printf("CRDS = %f", crds);
	
	return (ajb-csg-crds);
}

int main(int argc, char **argv)
{
	int cachet, nb_date;
	float indem_net, annuel, mensuel;
	while(1) {
		printf("entrez le montant du cachet global :\n");
		scanf("%d", &cachet);
		printf("entrez le nb cachet\n");
		scanf("%d", &nb_date);
		indem_net = calcul_indeminitees((float)cachet, nb_date);
		printf("\nindemnitées journalière net = %f\n", indem_net);
		annuel = indem_net*(365.0f)-(float)nb_date*indem_net*1.3f+(float)nb_date*(float)cachet*RAPPORT_GLOBAL_NET_CHANT;
		mensuel = annuel/12.0f;
		printf("cachet net : %f\n", (float)cachet*RAPPORT_GLOBAL_NET_CHANT);
		printf("cachet brut : %f\n", (float)cachet*RAPPORT_GLOBAL_BRUT_CHANT);
		printf("cachet global : %d\n", cachet);
		printf("salaire annuel : %f\n", annuel);
		printf("salaire mensuel : %f\n\n\n", mensuel);
	}
	return 0;
}
