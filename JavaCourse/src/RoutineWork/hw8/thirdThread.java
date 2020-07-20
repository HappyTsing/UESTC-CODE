package RoutineWork.hw8;

class thirdThread implements Runnable {
    public void run() {
        try {
            System.out.println("\t\tThird thread starts running.");
            for(int i=10; i>0; i--) {
                System.out.println("\t\tThird " + i);
                Thread.sleep(1000);
            }
            System.out.println("\t\tThird thread finished.");
        }catch(InterruptedException e) {}
    }
}