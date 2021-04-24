#include <stdio.h>

extern struct rtpkt {
    int sourceid;       /* id of sending router sending this pkt */
    int destid;         /* id of router to which pkt being sent
                         (must be an immediate neighbor) */
    int mincost[4] ;    /* min cost to node 0 ... 3 */
};

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
    int costs[4][4];
} dt3;

/* students to write the following two routines, and maybe some others */

void rtinit3()
{
    dt3.costs[3][0] = 7;

//    not directly attached neighbor
    dt3.costs[3][1] = 9999;


    dt3.costs[3][2] = 2;
    dt3.costs[3][3] = 0;
}


void rtupdate3(rcvdpkt)
struct rtpkt *rcvdpkt;

{
    //    for each cost in mincosts
    for(int i = 0; i < 4; i++)
    {

//        set cost from source node (1 if received from node 1) to node i = cost in mincosts[i]
        dt3.costs[rcvdpkt->sourceid][i] = rcvdpkt->mincost[i];
    }
}


printdt3(dtptr)
struct distance_table *dtptr;

{
printf("             via     \n");
printf("   D3 |    0     2 \n");
printf("  ----|-----------\n");
printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}







