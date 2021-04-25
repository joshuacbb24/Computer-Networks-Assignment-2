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


// we added this in
// gets instantiated in init to keep track of directly connected neighbors
// a 1 in a particular spot indicates that the node is a direct neighbor
// E.G. if position 3 is 1, then node 3 is a direct neighbor of this node
// we did not make const, because in a real network scenario, your directly attached neighbors could change
// THIS VARIABLE IS NOT ACCESSIBLE OUTSIDE OF THIS C FILE
static int direct_neighbors3[4] = {0};



/* students to write the following two routines, and maybe some others */

void rtinit3()
{
    //    start all values at 9999 (infinity)
    for(int i = 0; i < 4; i++)
    {

        for(int j = 0; j < 4; j++)
        {
            dt3.costs[i][j] = 9999;
        }
    }




    dt3.costs[3][0] = 7;



    dt3.costs[3][2] = 2;
    dt3.costs[3][3] = 0;



    direct_neighbors3[0] = 1;
    direct_neighbors3[2] = 1;

}


void rtupdate3(rcvdpkt)
struct rtpkt *rcvdpkt;

{


//    stays 0 if no costs changed, otherwise will be 1
    int changed = 0;


//    for each of the values in rcvdpkt
    for(int i = 0; i < 4; i++)
    {

//        if any of the new values do not equal the corresponding old value
        if(dt3.costs[rcvdpkt->sourceid][i] != rcvdpkt->mincost[i])
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
            dt3.costs[rcvdpkt->sourceid][i] = rcvdpkt->mincost[i];
        }


//        create rtpkt to send updated entries
        struct rtpkt updatePacket;



//        for each node
        for(int i = 0;  i < 4; i++)
        {

//            if node i is a direct neighbor
            if(direct_neighbors3[i])
            {


//                create a rtpkt to send updated table to neighbors
//                set sourceid to 3, destination to neighbor's id, and cost row to the new row that was received
//                creatertpkt(updatePacket, 3, i, dt3.costs[rcvdpkt->sourceid]);

                printf("sending from %d and sending to %d\n", 3, i);

                updatePacket.sourceid = 3;
                updatePacket.destid = i;

//            copy costs into mincost array
                for(int j = 0; j < 4; j++)
                {
                    updatePacket.mincost[j] = dt3.costs[0][j];
                }


//                send update packet to layer 2
                tolayer2(updatePacket);


            }


        }

//        send rtpkt



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







