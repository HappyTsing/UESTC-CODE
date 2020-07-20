package RoutineWork.hw8;

class FirstThread implements Runnable {
    public void run() {
        try {
            System.out.println("First thread starts running.");
            for(int i=1; i<11; i++) {
                System.out.println("First " + i);
                Thread.sleep(1000);
            }
            System.out.println("First thread finishes running.");
        } catch (InterruptedException e) {}
    }
}
