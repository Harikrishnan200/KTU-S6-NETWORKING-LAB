
#include <stdio.h>
#include <stdlib.h>

void main()
{
    int bucket_capacity = 0, outflow_size = 0;

    // Accept Bucket Capacity
    printf("\n\nEnter bucket capacity: ");
    scanf("%d", &bucket_capacity);
    
    // Accept Packet Outflow Size
    printf("Enter packet outflow size: ");
    scanf("%d", &outflow_size);
    
    printf("\n");
    
    int incoming_packets_size = 0, available_size = bucket_capacity, used_size = 0, packet_overflow = 0;
    
    while(1)
    {
        printf("\n[Enter -1 to exit]");
        
        // Accept Incoming Packets Size
        printf("\nEnter the incoming packets size: ");
        scanf("%d", &incoming_packets_size);
        
        // Check whether user needs to exit
        if(incoming_packets_size == -1)
        {
            printf("\nExit\n\n");
            exit(0);
        }
        else
        {
            // Check whether space available in bucket and drop overflowed packets
            if(incoming_packets_size <= available_size)
                available_size -= incoming_packets_size;
            else
            {
                printf("\nDropped %d packet(s).", (incoming_packets_size - available_size));
                available_size = 0;
            }
            
            // Calculate used size
            used_size = bucket_capacity - available_size;
            
            // Check whether outflow size is more than used size
            if(outflow_size > used_size)
            {
                printf("\nOutflow size changed from %d to %d.", outflow_size, used_size);
                outflow_size = used_size;
            }
            
            // Print Bucket Usage
            printf("\nBucket size of %d used out of %d.", used_size, bucket_capacity);
            
            // Leak out packets
            printf("\nLeaked out %d packet(s).\n", outflow_size);
            available_size += outflow_size;
        }
    }
}