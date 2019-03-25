main()
{
    int distance_cover=0;
    int curser_posi=0;
    int pre_posi=0;

        printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @\n\n");
        printf("   -----CYLINDER COUNT------\n\n");
        printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @\n");
            curser_posi=143;
            pre_posi=123;
            int my_queue[] = {86,1470,913,1774,948,1509,1022,1750,130};

            pre_posi = curser_posi;
            for(int i=0;i<=9;i++)
            {
                curser_posi = my_queue[i];
                distance_cover = distance_cover + abs(curser_posi-pre_posi);
                pre_posi = curser_posi;
            }

        printf("\nTOTAL NUMBER OF CYLINDER ARE : %d",distance_cover);
        printf("\n\n@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @\n");

}
