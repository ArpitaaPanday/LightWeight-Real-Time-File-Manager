#!/bin/bash
echo "Starting stress test..."
for i in {1..1000}
do
    touch /tmp/testfile_$i
    echo "Test $i" >> /tmp/testfile_$i
    rm /tmp/testfile_$i
done
echo "Stress test completed."