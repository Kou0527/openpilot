import time
from cereal.messaging import SubMaster
from common.realtime import DT_MDL
from common.params import Params


def all_dead(managerState):
  # return if all processes that should be dead are dead
  return all([not p.running or p.shouldBeRunning for p in managerState.processes])


if __name__ == "__main__":
  params = Params()
  params.put_bool("FakeIgnition", False)

  sm = SubMaster(["driverStateV2", "managerState", "deviceState"])
  occurrences = 0

  while 1:
    params.put_bool("FakeIgnition", True)
    sm.update(0)
    dmon_frame = None

    print('Waiting for driverStateV2')
    st = time.monotonic()
    timeout = 15  # s

    # successful if we get 100 messages from dmonitoringmodeld (5s)
    while time.monotonic() - st < timeout:
      sm.update(0)
      time.sleep(DT_MDL)
      if sm.updated["driverStateV2"]:
        if dmon_frame is None:
          dmon_frame = sm.rcv_frame['driverStateV2']

        if (sm.rcv_frame['driverStateV2'] - dmon_frame) > (5 / DT_MDL):
          print('Got driverStateV2! Exiting', sm.rcv_frame['driverStateV2'], dmon_frame)
          time.sleep(1)
          break
    else:
      print('WARNING: timed out in 15s waiting for 100 messages from dmonitoringmodeld, occurrences:', occurrences, sm.rcv_frame['driverStateV2'], dmon_frame)
      occurrences += 1

    params.put_bool("FakeIgnition", False)
    while sm['deviceState'].started:
      sm.update(0)
      time.sleep(0.05)

    while not sm.updated['managerState']:
      sm.update(0)
      time.sleep(0.05)

    st = time.monotonic()
    while not all_dead(sm['managerState']) and (time.monotonic() - st < timeout):
      sm.update(0)
      time.sleep(0.1)

    if not all_dead(sm['managerState']):
      print('WARNING: timed out waiting for processes to die')
      time.sleep(5)
    else:
      print('all dead')
