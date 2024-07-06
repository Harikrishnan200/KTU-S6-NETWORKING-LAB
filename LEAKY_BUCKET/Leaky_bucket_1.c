#include<stdio.h>
int main(){
    int incoming_packet,outgoing_rate=0,bucket_size,store=0,n;
    printf("Enter the bucket size: ");
    scanf("%d",&bucket_size);
    printf("Enter the number of incoming packets:");
    scanf("%d",&n);
    printf("Enter the outgoing rate:");
    scanf("%d",&outgoing_rate);
    
    while (n!=0){
        printf("\nEnter the size of incoming packet:");
        scanf("%d",&incoming_packet);
        printf("\nIncoming packet size = %d",incoming_packet);
        
        if(incoming_packet <= (bucket_size-store)){
            store += incoming_packet;
            printf("\nBucket size is %d out of %d",store,bucket_size);
        }else{
            printf("\nDroped packets = %d",incoming_packet-(bucket_size-store));
            store = bucket_size;
            printf("\nBucket size is %d out of %d",store,bucket_size);
        }
        store -= outgoing_rate;
        if(store<0) store = 0;
        printf("\nAfter outgoing rate the bucket size is: %d",store);
        n--;
    }
    





    return 0;
}


// output:
// Enter the bucket size: 50
// Enter the number of incoming packets:5
// Enter the outgoing rate:10

// Enter the size of incoming packet:20

// Incoming packet size = 20
// Bucket size is 20 out of 50
// After outgoing rate the bucket size is: 10
// Enter the size of incoming packet:30

// Incoming packet size = 30
// Bucket size is 40 out of 50
// After outgoing rate the bucket size is: 30
// Enter the size of incoming packet:30

// Incoming packet size = 30
// Droped packets = 10
// Bucket size is 50 out of 50
// After outgoing rate the bucket size is: 40
// Enter the size of incoming packet:20

// Incoming packet size = 20
// Droped packets = 10
// Bucket size is 50 out of 50
// After outgoing rate the bucket size is: 40
