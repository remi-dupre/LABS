import json
import glob
import matplotlib.pyplot as plt

file_tests = open('../data/tests.json')
tests_set = json.loads(file_tests.read())

def compare_algo(tests):
    dimension_dict = {}
    fig = plt.figure()
    for test in tests:
        if test['dim'] not in dimension_dict.keys():
            dimension_dict[test['dim']] = {'name':[],'running_time':[],'merit':[]}
        name = test['name']
        for p in test['params']:
            name = name + ' ' + '\n' + p + '=' + str(test['params'][p])
        dimension_dict[test['dim']]['name'].append(name)
        dimension_dict[test['dim']]['running_time'].append(test['running_time'])
        dimension_dict[test['dim']]['merit'].append(test['merit'])
    for N in dimension_dict.keys():
        for i in range(len(dimension_dict[N]['merit'])):
            plt.scatter(dimension_dict[N]['running_time'][i],
            dimension_dict[N]['merit'][i])
            plt.annotate(dimension_dict[N]['name'][i],
            (dimension_dict[N]['running_time'][i],
            dimension_dict[N]['merit'][i]))
        plt.xlabel('running time')
        plt.ylabel('merit')
        fig.suptitle('Comparison in results and runtime of the different algorithm')
        #plt.show()
        fig.savefig('../figure/compare'+str(N)+'.png', dpi=fig.dpi)

def convergence_in_nb_step(tests):
    step_tests = [x  for x in tests if x['steps'] != {}]
    for test in step_tests:
        max_so_far = 0
        result = []
        for s in test['steps'].keys():
            max_so_far = max (max_so_far, test['steps'][s]['merit'])
            result.append(max_so_far)
        runtime = [ test['steps'][s]['time'] for s in test['steps']]
        merit = [ test['steps'][s]['merit'] for s in test['steps']]
        fig = plt.figure()
        plt.plot(runtime,result,'b')
        plt.plot(runtime,merit,'b', alpha=0.3)
        plt.xlabel('running time')
        plt.ylabel('merit')
        fig.suptitle('Convergence of the algorithm ' + test['name'])
        #plt.show()
        fig.savefig('../figure/convergence'+test['name']+'.png', dpi=fig.dpi)

def evolution_in_dimension(tests):
    algo_dict = {}
    for test in tests:
        if test['name'] not in algo_dict.keys():
            algo_dict[test['name']] = {'dimension':[],'running_time':[],'merit':[]}
        else:
            algo_dict[test['name']]['dimension'].append(test['dim'])
            algo_dict[test['name']]['running_time'].append(test['running_time'])
            algo_dict[test['name']]['merit'].append(test['merit'])
    fig = plt.figure()
    for algo in algo_dict.keys():
        plt.plot(algo_dict[algo]['dimension'],algo_dict[algo]['merit'], label=algo)
    plt.xlabel('dimension')
    plt.ylabel('merit')
    plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.12))
    fig.suptitle('Evolution of the merit of the algorithms ' + '\n depending on the dimension', fontsize=12)
    fig.savefig('../figure/dimension_merit'+'.png', dpi=fig.dpi, bbox_inches='tight')
    fig = plt.figure()
    for algo in algo_dict.keys():
        plt.plot(algo_dict[algo]['dimension'],algo_dict[algo]['running_time'], label=algo)
    plt.xlabel('dimension')
    plt.ylabel('runtime')
    plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.12))
    fig.suptitle('Evolution of the runtime of the algorithms ' + '\n depending on the dimension', fontsize=12)
    fig.savefig('../figure/dimension_runtime'+'.png', dpi=fig.dpi, bbox_inches='tight')

def evolution_in_param(param, tests):
    param_dict = {param : [], 'running_time' : [], 'merit' : []}
    name = ''
    for test in tests:
        name = test['name']
        param_dict[param].append(test['params'][param])
        param_dict['running_time'].append(test['running_time'])
        param_dict['merit'].append(test['merit'])
    fig = plt.figure()
    plt.plot(param_dict[param],param_dict['merit'], label=param)
    plt.xlabel(param)
    plt.ylabel('merit')
    plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.12))
    fig.suptitle('Evolution of the merit of algorithm ' + name + '\n depending on the dimension', fontsize=12)
    fig.savefig('../figure/param_merit_' + name + '_' + param + '.png', dpi=fig.dpi, bbox_inches='tight')
    fig = plt.figure()
    plt.plot(param_dict[param],param_dict['running_time'], label=param)
    plt.xlabel(param)
    plt.ylabel('runtime')
    plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.12))
    fig.suptitle('Evolution of the runtime of algorithm ' + name + '\n depending on the dimension', fontsize=12)
    fig.savefig('../figure/dimension_runtime_' + name + '_' + param + '.png', dpi=fig.dpi, bbox_inches='tight')

for tests in tests_set:
    if tests['type'] == "compare":
        compare_algo(tests['dataset'])
        convergence_in_nb_step(tests['dataset'])
    if tests['type'] == "benchmark" and tests['abciss'] == "dim":
        evolution_in_dimension(tests['dataset'])
    elif tests['type'] == "benchmark":
        evolution_in_param(tests['abciss'],tests['dataset'])
