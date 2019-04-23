//
//  nearest.h
//  flag_bacon
//
//  Created by Stephan Schulz on 2019-04-20.
//

//https://codereview.stackexchange.com/questions/108566/n-closest-points-to-the-reference-point
#ifndef nearest_h
#define nearest_h

struct customPoint {
    double x;
    double y;
    double z;
    
    bool operator==(const customPoint& rhp) {
        return x == rhp.x && y == rhp.y && z == rhp.z;
    }
    
};

class nearest{
private:
    
public:
    
    // to print Point to cout
//    std::ostream& operator<<(std::ostream &o, const customPoint& p) {
//        o << "(" << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;
//        return o;
//    }
    
    // defines sorting order for points
    struct ByDistance {
        const customPoint& origin;
        
        bool operator()(const customPoint& lp, const customPoint& rp) {
            return dist(origin, lp) < dist(origin, rp);
        }
        
        static double dist(const customPoint& lp, const customPoint& rp){
            double xs = (lp.x - rp.x) * (lp.x - rp.x);
            double ys = (lp.y - rp.y) * (lp.y - rp.y);
            double zs = (lp.z - rp.z) * (lp.z - rp.z);
            return sqrt(xs + ys + zs);
        }
    };
    
    vector<customPoint> nearestN(const vector<customPoint>& points, int N) {
        if (points.size() == 0) {
            vector<customPoint> empty;
            return empty;
        }
        return nearestN(points, N, points[0], INFINITY);
    }
    
    vector<customPoint> nearestN(const vector<customPoint>& points,
                           int N,
                           const customPoint& reference,
                           double distanceThreshold) {
        
        vector<customPoint> temp;
        temp.insert(temp.begin(), points.begin(), points.end());
        
        // filtering vector to remove all points far then distance from reference
        temp.erase(remove_if(temp.begin(), 
                             temp.end(),
                             [&reference, distanceThreshold](customPoint& p){ return ByDistance::dist(p, reference) > distanceThreshold; }),
                   temp.end());
        
        ByDistance distance = {reference};
        sort(temp.begin(), temp.end(), distance);
        
        auto sz = min(static_cast<int>(temp.size()), N);
        vector<customPoint> result(sz);
        copy_n(temp.begin(), sz, result.begin());
        return result;
    }
    
};

#endif /* nearest_h */
