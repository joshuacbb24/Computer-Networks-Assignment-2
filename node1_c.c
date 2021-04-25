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

int connectcosts1[4] = { 1,  0,  1, 999 };


// we added this in
// gets instantiated in init to keep track of directly connected neighbors
// a 1 in a particular spot indicates that the node is a direct neighbor
// E.G. if position 3 is 1, then node 3 is a direct neighbor of this node
// we did not make const, because in a real network scenario, your directly attached neighbors could change
// THIS VARIABLE IS NOT ACCESSIBLE OUTSIDE OF THIS C FILE
static int direct_neighbors1[4] = {0};



struct distance_table
{
    int costs[4][4];
} dt1;


/* students to write the following two routines, and maybe some others */


rtinit1()
{

    //    start all values at 9999 (infinity)
    for(int i = 0; i < 4; i++)
    {

        for(int j = 0; j < 4; j++)
        {
            dt1.costs[i][j] = 9999;
        }
    }


    dt1.costs[1][0] = 1;
    dt1.costs[1][1] = 0;

    dt1.costs[1][2] = 1;



    direct_neighbors1[0] = 1;
    direct_neighbors1[2] = 1;




}


rtupdate1(rcvdpkt)
struct rtpkt *rcvdpkt;

{



    //    stays 0 if no costs changed, otherwise will be 1
    int changed = 0;


    //    for each of the values in rcvdpkt
    for(int i = 0; i < 4; i++)
    {

        //        if any of the new values do not equal the corresponding old value
        if(dt1.costs[rcvdpkt->sourceid][i] != rcvdpkt->mincost[i])
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
            dt1.costs[rcvdpkt->sourceid][i] = rcvdpkt->mincost[i];
        }


        //        create rtpkt to send updated entries
        struct rtpkt updatePacket;



        //        for each node
        for(int i = 0;  i < 4; i++)
        {

            //            if node i is a direct neighbor
            if(direct_neighbors1[i])
            {


                //                create a rtpkt to send updated table to neighbors
                //                set sourceid to 1, destination to neighbor's id, and cost row to the new row that was received
                creatertpkt(updatePacket, 1, i, dt1.costs[rcvdpkt->sourceid]);



                //                send update packet to layer 2
                tolayer2(updatePacket);


            }


        }

        //        send rtpkt



    }




}


printdt1(dtptr)
struct distance_table *dtptr;

{
printf("             via   \n");
printf("   D1 |    0     2 \n");
printf("  ----|-----------\n");
printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



linkhandler1(linkid, newcost)
int linkid, newcost;
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */

{
}


