#include<stdio.h> /*Header file*/
#include<stdlib.h>
#include<math.h>

#define Pi 3.1415926535898
#define G pow(6.674,-11)

struct StateStruct
{
double mM, mE, mS, rE, rM, xS, yS, vSx, vSy, vS, dES, thetaS, xM, yM, vMx, vMy, dEM, thetaM, xE, yE, vEx, vEy, t_step, dMS, obj, clear, tol;
};

struct ForceStruct
{
double F_MSx, F_MSy, F_SMx, F_SMy;
double F_ESx, F_ESy, F_SEx, F_SEy;
double F_EMx, F_EMy, F_MEx, F_MEy;
};

void initialize(struct StateStruct *State);
void g_forces(struct StateStruct *State, struct ForceStruct *Force);
void velocities(struct StateStruct *State, struct ForceStruct *Force);
void positions(struct StateStruct *State);


////////////////////main////////////////////////
void main(int argc, char *argv[])
{
struct StateStruct *State;
State = (struct StateStruct *) malloc(sizeof(struct StateStruct));
struct ForceStruct *Force;
Force = (struct ForceStruct *) malloc(sizeof(struct ForceStruct));

State->obj = atof(argv[1]);
State->clear = atof(argv[2]);
State->tol = atof(argv[3]);

if (State->obj == 1)
{

int i;
int count;
int magcount;
i = 0;
magcount = 0;
int angle;
angle = 0;

while (i != 2){

	State->vS = State->vS + State->tol*magcount;

	while (angle < 360 && i != 2){

		initialize(State);
		State->thetaS = State->thetaS + angle*(Pi/180);
		State->vSx = State->vS*cos(State->thetaS);
		State->vSy = State->vS*sin(State->thetaS);
		count = 0;
		printf("magcount: %d \n", magcount);
		printf("vS is %f \n ", State->vS);

			while (i ==0)
		
				{if (State->dMS <= State->rM + State->clear)
					{printf("Crashed into moon or below clearance \n");
					i = 1;
				}

				else if (State->dES <= State->rE)
					{printf("Returned to Earth \n");
					i = 2;
				}

				else if (State->dES >= 2*State->dEM)
					{printf("Lost in space \n");
					i = 3;
				}

				else if (count*State->t_step > 1000000)
					{printf("Time expired \n");
					i = 4;
				}

				else
				{
					g_forces(State, Force);
					velocities(State, Force);
					positions(State);
					count++;
					//printf("%d \n", count);
				}
			}
		angle = angle + 30;
		i=0;
		}
	magcount++;
	angle = 0;
	}
}

}


/////////////////////////////////Functions////////////////////////

//Initialize
void initialize(struct StateStruct *State)
{
double mM, mE, mS, rE, rM, xS, yS, vSx, vSy, vS, dES, thetaS, xM, yM, vMx, vMy, vM, dEM, thetaM, xE, yE, vEx, vEy, t_step, dMS, obj, clear, tol;

//double mM, mE, mS, rE, rM, clear, t_step;
mM = pow(7.34767309,22); /*mass of moon (kg)*/
mE = pow(5.97219,24); /*mass of Earth (kg)*/
mS = 28833; /*mass of spacecraft (kg)*/
rM = 1737100; /*radius of moon (m)*/
rE = 637100; /*radius of Earth (m)*/
rM = rM+(*State).clear;
t_step = 1;

//double xS, yS, vSx, vSy, vS, dES, thetaS, xM, yM, vMx, vMy, vM, dEM, thetaM, xE, yE, vEx, vEy, dMS;
xE = 0;
yE = 0;
vEx = 0;
vEy = 0;
vS = 1000;
thetaS = 50*(Pi/180);
dES = 340000000;
xS = dES*cos(thetaS);
yS = dES*sin(thetaS);
vSx = vS*cos(thetaS);
vSy = vS*sin(thetaS);

thetaM = 42.5*(Pi/180);
dEM = 384403000;
xM = dEM*cos(thetaM);
yM = dEM*sin(thetaM);
vM = pow(pow(G*mE,2)/((mE + mM)*dEM),0.5);
vMx = -vM*sin(thetaM);
vMy = vM*cos(thetaM);

dMS = pow(pow(xM-xS,2)+pow(yM-yS,2),0.5);


(*State).mM = mM;
(*State).mE = mE;
(*State).mS = mS;
(*State).rE = rE;
(*State).rM = rM;
(*State).xS = xS;
(*State).yS = yS;
(*State).vSx = vSx;
(*State).vSy = vSy;
(*State).vS = vS;
(*State).dES = dES;
(*State).thetaS = thetaS;
(*State).xM = xM;
(*State).yM = yM;
(*State).vMx = vMx;
(*State).vMy = vMy;
(*State).dEM = dEM;
(*State).thetaM = thetaM;
(*State).xE = xE;
(*State).yE = yE;
(*State).vEx = vEx;
(*State).vEy = vEy;
(*State).t_step = t_step;
(*State).dMS = dMS;

}



//g_forces
void g_forces(struct StateStruct *State, struct ForceStruct *Force)
{
double mM, mE, mS, rE, rM, xS, yS, vSx, vSy, vS, dES, thetaS, xM, yM, vMx, vMy, dEM, thetaM, xE, yE, vEx, vEy, t_step, dMS, obj, clear, tol;
double F_MSx, F_MSy, F_SMx, F_SMy;
double F_ESx, F_ESy, F_SEx, F_SEy;
double F_EMx, F_EMy, F_MEx, F_MEy;

//Gravity on spacecraft by moon
xM = (*State).xM;
yM = (*State).yM;

xS = (*State).xS;
yS = (*State).yS;

F_MSx = G*(*State).mM*(*State).mS*(xM-xS)/(pow((*State).dMS,3));
F_MSy = G*(*State).mM*(*State).mS*(yM-yS)/(pow((*State).dMS,3));
F_SMx = -F_MSx;
F_SMy = -F_MSy;

(*Force).F_MSx = F_MSx;
(*Force).F_MSy = F_MSy;
(*Force).F_SMx = F_SMx;
(*Force).F_SMy = F_SMy;

//Gravity on spacecraft by Earth
xE = (*State).xE;
yE = (*State).yE;

xS = (*State).xS;
yS = (*State).yS;

F_ESx = G*(*State).mE*(*State).mS*(xE-xS)/(pow((*State).dES,3));
F_ESy = G*(*State).mE*(*State).mS*(yE-yS)/(pow((*State).dES,3));
F_SEx = -F_ESx;
F_SEy = -F_ESy;

(*Force).F_ESx = F_ESx;
(*Force).F_ESy = F_ESy;
(*Force).F_SEx = F_SEx;
(*Force).F_SEy = F_SEy;

//Gravity on moon by Earth
xE = (*State).xE;
yE = (*State).yE;

xM = (*State).xM;
yM = (*State).yM;

F_EMx = G*(*State).mE*(*State).mM*(xE-xM)/(pow((*State).dEM,3));
F_EMy = G*(*State).mE*(*State).mM*(yE-yM)/(pow((*State).dEM,3));
F_MEx = -F_EMx;
F_MEy = -F_EMy;

(*Force).F_EMx = F_EMx;
(*Force).F_EMy = F_EMy;
(*Force).F_MEx = F_MEx;
(*Force).F_MEy = F_MEy;

}



//velocities
void velocities(struct StateStruct *State, struct ForceStruct *Force)
{
double mM, mE, mS, rE, rM, xS, yS, vSx, vSy, vS, dES, thetaS, xM, yM, vMx, vMy, dEM, thetaM, xE, yE, vEx, vEy, t_step, dMS, obj, clear, tol;
double F_MSx, F_MSy, F_SMx, F_SMy;
double F_ESx, F_ESy, F_SEx, F_SEy;
double F_EMx, F_EMy, F_MEx, F_MEy;
double vSx2, vSy2, vMx2, vMy2;

vSx2 = (*State).vSx + (((*State).t_step*(*Force).F_MSx + (*Force).F_ESx)/(*State).mS);
vSy2 = (*State).vSy + (((*State).t_step*(*Force).F_MSy + (*Force).F_ESy)/(*State).mS);

vMx2 = (*State).vMx + (((*State).t_step*(*Force).F_EMx + (*Force).F_SMx)/(*State).mM);
vMy2 = (*State).vMy + (((*State).t_step*(*Force).F_EMy + (*Force).F_SMy)/(*State).mM);

(*State).vSx = vSx2;
(*State).vSy = vSy2;
(*State).vMx = vMx2;
(*State).vMy = vMy2;
}



//positions
void positions(struct StateStruct *State)
{
double mM, mE, mS, rE, rM, xS, yS, vSx, vSy, vS, dES, thetaS, xM, yM, vMx, vMy, dEM, thetaM, xE, yE, vEx, vEy, t_step, dMS, obj, clear, tol;
double F_MSx, F_MSy, F_SMx, F_SMy;
double F_ESx, F_ESy, F_SEx, F_SEy;
double F_EMx, F_EMy, F_MEx, F_MEy;
double xS2, yS2, xM2, yM2, dES2, dEM2, dMS2, thetaS2, thetaM2;

xS2 = (*State).xS + (*State).t_step*(*State).vSx;
yS2 = (*State).yS + (*State).t_step*(*State).vSy;

xM2 = (*State).xM + (*State).t_step*(*State).vMx;
yM2 = (*State).yM + (*State).t_step*(*State).vMy;

dES2 = pow(pow((*State).xE - (*State).xS,2) + pow((*State).yE - (*State).yS,2),0.5);
dEM2 = pow(pow((*State).xE - (*State).xM,2) + pow((*State).yE - (*State).yM,2),0.5);
dMS2 = pow(pow((*State).xM - (*State).xS,2) + pow((*State).yM - (*State).yS,2),0.5);

//thetaS2 = acos((*State).xS/dES2);
//thetaM2 = acos((*State).xM/dEM2);

(*State).xS = xS2;
(*State).yS = yS2;
(*State).xM = xM2;
(*State).yM = yS2;
(*State).dES = dES2;
(*State).dEM = dEM2;
(*State).dMS = dMS2;
//(*State).thetaS = thetaS2;
(*State).thetaM = thetaM2;
}
