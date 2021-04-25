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

    const int cur_node = 3;


    //    for each cost in mincosts
    for(int i = 0; i < 4; i++)
    {

//        set cost from source node (E.G. 1 if received from node 1) to each destination from updated entries
        dt3.costs[rcvdpkt->sourceid][i] = rcvdpkt->mincost[i];
    }





    //        re-calculate minimum costs in the node's row where it is the source
    for(int dest = 0; dest < 4; dest++)
    {


//                will store the minimum of various cost calculations
        int new_cost = 9999999;



//                for every node j
        for(int j = 0; j  < 4; j++)
        {

//                    cost from current node to node j
            int cost = dt3.costs[cur_node][j];


//                    add cost from node j to dest
            cost += dt3.costs[j][dest];


//                    update if new minimum has been calculated
            if(cost < new_cost)
            {
                new_cost = cost;
            }


        }



//                if the new calculated cost doesn't equal the previous cost in the table
        if(new_cost != dt3.costs[cur_node][dest])
        {

//                    update the value
            dt3.costs[cur_node][dest] = new_cost;

//                    there was a change in minimum costs
            changed = 1;
        }
    }





//    if there was any change in the minimum costs
    if(changed == 1)
    {

//        create rtpkt to send updated entries
        struct rtpkt updatePacket;



//        for each node i
        for(int i = 0;  i < 4; i++)
        {

//            if node i is a direct neighbor
            if(direct_neighbors3[i])
            {


//                create a rtpkt to send updated table to neighbors
//                set sourceid to 0, destination to neighbor's id, and cost row to the new row that was received
//                creatertpkt causes a segmentation fault, so doing it manually


                updatePacket.sourceid = cur_node;
                updatePacket.destid = i;


//                copy each minimum cost into mincost array
                for(int j = 0; j < 4; j++)
                {
                    updatePacket.mincost[j] = dt3.costs[cur_node][j];
                }


//                send update packet to layer 2
                tolayer2(updatePacket);


            }


        }




    }





}






// changed the print dt function to print the whole dt
// !!! THIS IS ONLY EXTERN SO THAT PRINTING OF DISTANCE TABLES CAN BE DONE IN PROG3_C TO SHOW FINAL RESULT !!!
extern printdt3()
{

    printf("\t\t\tCOST TO:\n");

//    header
    printf("\tD3   \t\t0 \t\t1 \t\t2 \t\t3\n");

    for(int row = 0; row < 4; row++)
    {

        if(row == 2)
        {
            printf("FROM: ");
        }

        printf("\t%d |\t ", row);

        for(int column = 0; column < 4; column++)
        {



//            print each value in table
            printf("\t%d \t", dt3.costs[row][column]);
        }

        printf("\n");
    }
    printf("\n");

}







