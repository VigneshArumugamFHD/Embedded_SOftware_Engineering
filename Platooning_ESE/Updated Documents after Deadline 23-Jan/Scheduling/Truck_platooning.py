from pycpa import schedulers
from pycpa import analysis
from pycpa import graph
from pycpa import model
from pycpa import options
from pycpa import plot
from pycpa import path_analysis
import time

# initialize pycpa
options.init_pycpa()

# options.set_opt(,value=True)
truck_platooning = model.System('Truck Platooning Model')

# define computational resources
core_0 = model.Resource("core0",schedulers.SPPScheduler())


# define GPU overclocking factor
over_clock_factor_gpu = 2

# bind resources to the system
truck_platooning.bind_resource(core_0)


# define system tasks

gps_task     = model.Task('gps'    , wcet = 1   , bcet = 1 , scheduling_parameter = 1)

lidar_task    = model.Task('lidar'  , wcet = 1   , bcet = 1 , scheduling_parameter = 1)

camera_task  = model.Task('camera', wcet = 1   , bcet = 1 , scheduling_parameter = 1)

pcu_task     = model.Task('pcu'         , wcet = 1.5   , bcet = 1 , scheduling_parameter = 1)

wifi_task       = model.Task('wifi'      , wcet = 1   , bcet = 1 , scheduling_parameter = 1)

# bind tasks to resources

core_0.bind_task(gps_task)

core_0.bind_task(lidar_task)

core_0.bind_task(camera_task)

core_0.bind_task(pcu_task)

core_0.bind_task(wifi_task)


# event models for respective tasks
# tSFM.in_event_model = model.PJdEventModel(P = 33)

# tLocalization_pre.in_event_model = model.PJdEventModel(P = 400)
# tLocalization_pre.link_dependent_task(tLocalization_gpu)
# tLocalization_gpu.link_dependent_task(tLocalization_post)

gps_task.in_event_model = model.PJdEventModel(P = 6)
lidar_task.in_event_model = model.PJdEventModel(P = 6)
camera_task.in_event_model = model.PJdEventModel(P = 6)
pcu_task.in_event_model = model.PJdEventModel(P = 6)
wifi_task.in_event_model = model.PJdEventModel(P = 6)

# tDetection_pre.in_event_model = model.PJdEventModel(P = 200)
# tDetection_pre.link_dependent_task(tDetection_gpu)
# tDetection_gpu.link_dependent_task(tDetection_post)

# tLane_detection.in_event_model = model.PJdEventModel(P = 66)


# bind offloading paths to the system
# p1 = truck_platooning.bind_path(model.Path('localization_offloading',[tLocalization_pre, tLocalization_gpu, tLocalization_post]))
# p2 = truck_platooning.bind_path(model.Path('detection_offloading',[tDetection_pre,tDetection_gpu,tDetection_post]))
# paths = [p1, p2]


g = graph.graph_system(truck_platooning, 'truck_platooning.pdf')
start_time = time.time()


# perform analysis
print("Performing analysis started")
results = analysis.analyze_system(truck_platooning)
# calculate the S1 latency for the first 50 events
i = 0
#for p in range(0, len(paths)):
 #   # for n in range(1, 6):
  #      best_case_latency, worst_case_latency = path_analysis.end_to_end_latency(paths[p], results, n = 1)
    #    print("stream %s e2e latency. best case: %d, worst case: %d" % (
    #    paths[p].name, best_case_latency, worst_case_latency))
    #    i += 1
# print the worst case response times (WCRTs)
print("Result:")
for r in sorted(truck_platooning.resources, key=str):
    for t in sorted(r.tasks, key=str):
        print("%s: wcrt=%f, bcrt = %f"  % (t.name, results[t].wcrt, results[t].bcrt))

print("---%s seconds---" % (time.time() - start_time))
