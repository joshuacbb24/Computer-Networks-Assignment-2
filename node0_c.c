#include <stdio.h>


extern struct rtpkt {
    int sourceid ;       /* id of sending router sending this pkt */
    int destid ;         /* id of router to which pkt being sent
                         (must be an immediate neighbor) */
    int mincost[4] ;    /* min cost to node 0 ... 3 */
};

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
    int costs[4][4];
} dt0;


/* students to write the following two routines, and maybe some others */

void rtinit0()
{

//    distance to itself
    dt0.costs[0][0] = 0;

//    distance to node 1
    dt0.costs[0][1] = 1;


//    distance to node 2
    dt0.costs[0][2] = 3;

//    distance to node 3
    dt0.costs[0][3] = 7;
}


void rtupdate0(rcvdpkt)
struct rtpkt *rcvdpkt;
{

//    stays 0 if no costs changed, otherwise will be 1
    int changed = 0;


    for(int i = 0; i < 4; i++)
    {
        if(dt0.costs[rcvdpkt->sourceid][i] != rcvdpkt->mincost[i])
        {
            changed = 1;
            break;
        }
    }


    if(changed)
    {
        //    for each cost in mincosts
        for(int i = 0; i < 4; i++)
        {

//        set cost from source node (1 if received from node 1) to node i = cost in mincosts[i]
            dt0.costs[rcvdpkt->sourceid][i] = rcvdpkt->mincost[i];
        }


//        create rtpkt
        struct rtpkt updatePacket;


//        for each node
        for(int i = 0;  i < 4; i++)
        {

//             TODO: need to actually make sure node is directly connected neighbor
            if(dt0.costs[0][i] < 9999 && i != 0)
            {
                creatertpkt(updatePacket, 0, i, dt0.costs[0]);
            }
        }

//        send rtpkt



    }

    else
    {

    }


}


printdt0(dtptr)
struct distance_table *dtptr;

{
    printf("                via     \n");
    printf("   D0 |    1     2    3 \n");
    printf("  ----|-----------------\n");
    printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],dtptr->costs[1][2],dtptr->costs[1][3]);
    printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],dtptr->costs[2][2],dtptr->costs[2][3]);
    printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],dtptr->costs[3][2],dtptr->costs[3][3]);
}

linkhandler0(linkid, newcost)
int linkid, newcost;

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */

{
}

