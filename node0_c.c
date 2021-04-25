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



// we added this in
// gets instantiated in init to keep track of directly connected neighbors
// a 1 in a particular spot indicates that the node is a direct neighbor
// E.G. if position 3 is 1, then node 3 is a direct neighbor of this node
// we did not make const, because in a real network scenario, your directly attached neighbors could change
// THIS VARIABLE IS NOT ACCESSIBLE OUTSIDE OF THIS C FILE
static int direct_neighbors0[4] = {0};



/* students to write the following two routines, and maybe some others */

void rtinit0()
{



//    start all values at 9999 (infinity)
    for(int i = 0; i < 4; i++)
    {

        for(int j = 0; j < 4; j++)
        {
            dt0.costs[i][j] = 9999;
        }
    }



    direct_neighbors0[1] = 1;
    direct_neighbors0[2] = 1;
    direct_neighbors0[3] = 1;



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


//    for each of the values in rcvdpkt
    for(int i = 0; i < 4; i++)
    {

//        if any of the new values do not equal the corresponding old value
        if(dt0.costs[rcvdpkt->sourceid][i] != rcvdpkt->mincost[i])
        {

//            there was a change in values
            changed = 1;
            break;
        }
    }


//    if there was a change
    if(changed)
    {
        //    for each cost in mincosts
        for(int i = 0; i < 4; i++)
        {

//        set cost from source node (E.G. 1 if received from node 1) to each destination from updated entries
            dt0.costs[rcvdpkt->sourceid][i] = rcvdpkt->mincost[i];
        }


//        create rtpkt to send updated entries
        struct rtpkt updatePacket;



//        for each node
        for(int i = 0;  i < 4; i++)
        {

//            if node i is a direct neighbor
            if(direct_neighbors0[i])
            {


//                create a rtpkt to send updated table to neighbors
//                set sourceid to 0, destination to neighbor's id, and cost row to the new row that was received
                creatertpkt(updatePacket, 0, i, dt0.costs[rcvdpkt->sourceid]);



//                send update packet to layer 2
                tolayer2(updatePacket);


            }


        }

//        send rtpkt



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

