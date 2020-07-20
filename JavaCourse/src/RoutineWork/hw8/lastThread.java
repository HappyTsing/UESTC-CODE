package RoutineWork.hw8;

class lastThread implements Runnable {
    public void run() {
        try {
            System.out.println("\t\t\tLast thread starts running.");
            for(int i=10; i>0; i--) {
                System.out.println("\t\t\tLast " + i);
                Thread.sleep(1000);
            }
            System.out.println("\t\t\tLast thread finished.");
        }catch(InterruptedException e) {}
    }
}