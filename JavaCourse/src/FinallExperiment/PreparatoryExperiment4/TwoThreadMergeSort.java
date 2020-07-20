package FinallExperiment.PreparatoryExperiment4;

public class TwoThreadMergeSort {
    public static void main(String[] args) {
        int length = 100;
        int[] data = (new Data(length)).getData();
        int[] temp = new int[data.length];
        printArr(data);
        System.out.println(); //换行

        int center = data.length/2;

        long Two_startTime=System.currentTimeMillis(); //获取开始时间
        new Thread(new Runnable() {
            @Override
            public void run() {
                mergeSort(data, temp, 0, center);
            }
        }).start();
        new Thread(new Runnable() {
            @Override
            public void run() {
                mergeSort(data, temp, center+1, data.length-1);
            }
        }).start();
        merge(data, temp, 0, center+1, data.length-1);
        long Two_endTime=System.currentTimeMillis();   //获取结束时间
        printArr(data);
        System.out.println("\n----多线程归并排序的时间为："+(Two_endTime-Two_startTime) +"ms");
    }


    //递归
    private static void mergeSort(int[] nums,int[] temp,int left,int right){
        if(left<right){
            int center = (left+ right) / 2;
            mergeSort(nums, temp, left, center);
            mergeSort(nums, temp, center + 1, right);
            merge(nums, temp, left, center + 1, right);

        }
    }

    //合并
    private static void merge(int[] nums, int[] temp, int leftbeg, int middle, int rightEnd) {

        int leftEnd = middle - 1;
        int tmpPos = leftbeg;
        int numElements = rightEnd - leftbeg + 1;

        while (leftbeg <= leftEnd && middle <= rightEnd) {
            if (nums[leftbeg] < nums[middle])
                temp[tmpPos++] = nums[leftbeg++];
            else
                temp[tmpPos++] = nums[middle++];
        }
        while (leftbeg <= leftEnd)
            temp[tmpPos++] = nums[leftbeg++];

        while (middle <= rightEnd)
            temp[tmpPos++] = nums[middle++];

        for (int i = 0; i < numElements; i++, rightEnd--)
            nums[rightEnd] = temp[rightEnd];
    }

    public static void printArr(int[] arr) {
        for(int i : arr){
            System.out.print(i+" ");
        }
    }
}

