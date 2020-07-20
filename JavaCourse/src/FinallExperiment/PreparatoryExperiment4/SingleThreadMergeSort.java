package FinallExperiment.PreparatoryExperiment4;

import java.util.Random;

public class SingleThreadMergeSort {

    public static void main(String[] args) {
        int length = 100;
        int[] data = (new Data(length)).getData();
        int[] temp = new int[data.length]; //创建临时数组
        printArr(data);
        System.out.println();  //换行
        long single_startTime=System.currentTimeMillis(); //获取开始时间
        mergeSort(data, temp, 0, data.length - 1);
        long single_endTime=System.currentTimeMillis();   //获取结束时间
        printArr(data);
        System.out.println("\n----单线程归并排序的时间为："+(single_endTime-single_startTime) +"ms");
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

//产生测试数据
class Data {
    int length;
    int[] data;

    public Data(int length) {
        this.length = length;
        data = new int[length];
    }

    public int[] getData() {

        Random random = new Random(System.currentTimeMillis());
        for (int i = 0; i < length; i++) {
            data[i] = random.nextInt(2 * length);
        }
        return data;
    }
}
