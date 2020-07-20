package RoutineWork.hw8;


class SecondThread implements Runnable {
    public void run() {
        try {
            System.out.println("\tSecond thread starts running.");
            for(int i=1; i<11; i++) {
                System.out.println("\tSecond " + i);
                Thread.sleep(1000);
            }
            System.out.println("\tSecond thread finished.");
        }catch(InterruptedException e) {}
    }
}
