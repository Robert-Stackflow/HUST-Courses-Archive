package homework.ch11_13.p2;

import java.util.ArrayList;

public class TaskServiceImpl implements TaskService {
    ArrayList<Task> taskArrayList = new ArrayList<>();

    public void executeTasks() {
        for (Task t : taskArrayList)
            t.execute();
    }

    public void addTask(Task t) {
        taskArrayList.add(t);
    }
}
