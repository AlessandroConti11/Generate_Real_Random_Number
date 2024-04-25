#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


/**
 * Return a random int between min and max, inclusive.
 * Obtain randomness from /dev/random file.
 *
 * @param min the min value.
 * @param max the max value.
 * @return the true random number
 */
int generateRandom(int min, int max) {
    /**
     * Storing an open file descriptor on /dev/random.
     * So we do not need to open the file every time.
     */
    static int devRandom = -1;
    /**
     * The pointer to the buffer where the read bytes will be stored.
     */
    char *nextRandomByte = NULL;
    /**
     * The number of Bytes to read from the buffer.
     */
    int byte2Read = 0;
    /**
     * The random value.
     */
    int randomValue = 0;
    /**
     * Random integer value read.
     */
    int bytesRead = 0;


    //check whether MAX >= MIN
    assert(max >= min);

    //if this is the 1st time that this function is called, open a /dev/random
    if(devRandom == -1) {
        //open file only for reading
        devRandom = open("/dev/random", O_RDONLY);

        //check whether the file has been opened correctly
        assert(devRandom != -1);
    }

    //read enough Bytes to fill an integer value
    nextRandomByte = (char *) &randomValue;
    byte2Read = sizeof(randomValue);

    //loop until we have read enough Bytes.
    // /dev/random is filled from user-generation action
    do {
        //read the specified number of bytes from the /dev/random file into the buffer
        bytesRead = read(devRandom, nextRandomByte, byte2Read);
        //reduce the Bytes to read from buffer
        byte2Read -= bytesRead;
        //update the pointer to the next buffer position
        nextRandomByte += bytesRead;
    } while (byte2Read > 0);

    return min + (randomValue % (max - min + 1));
}


/**
 * Main function.
 *
 * @return 0 if the programme is correctly terminated.
 */
int main(int argc, char *argv[]) {
    /**
     * Min value entered by the user.
     */
    int min = 0,
    /**
     * Max value entered by the user.
     */
    max = 0;
    /**
     * Random value.
     */
    int random = 0;
    /**
     * Return scanf value.
     */
    int returnScanf = 0;


    //insert the value from command line
    if(argc == 3) {
        min = atoi(argv[1]);
        max = atoi(argv[2]);
        argv[1] = 0x00;
        argv[2] = 0x00;
        assert(argv[1] == 0x00);
        assert(argv[2] == 0x00);
    }
    else{
        //insert the value
        printf("Insert the min: ");
        returnScanf = scanf("%d", &min);
        //the scanf read something
        assert(returnScanf > 0);

        printf("Insert the max: ");
        returnScanf = scanf("%d", &max);
        //the scanf read something
        assert(returnScanf > 0);
    }

    //max is greater then min
    assert(max >= min);

    //call the function
    random = generateRandom(min, max);

    //print the result
    printf("random value between %d and %d is: %d\n", min, max, random);

    return 0;
}
